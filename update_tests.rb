#!/usr/bin/ruby

$header_template = "testLisp/t_template.h"
$source_template = "testLisp/t_template.cpp"

def expand_template(template, out, base, tests)
	File.open(out, 'w') do |f|
		File.open(template).each do |line|
			if /%TESTS%/ =~ line
				tests.each do |test|
					f.write(test + "\n")
				end
			else
				f.write(line.gsub(/%NAME%/, base))
			end
		end
	end
end

def write_tests(base, t_header, t_source, tests)
	expand_template($header_template, t_header, base, tests)
	expand_template($source_template, t_source, base, tests)
end

def grep_tests(file)
	tests = []
	in_tests = false
	File.open(file).each do |line|
		if /\/\*TESTS:/ =~ line
			in_tests = true
		elsif /\*\// =~ line
			in_tests = false
		elsif in_tests
			test = line.gsub(/^\s*\*\s*/, "").gsub(/\n/, '')
			if test != ""
				tests << "assert(#{test});"
			end
		end	
	end
	return tests
end

def update_tests(base, header, source, t_header, t_source) 
	puts "testing " + header
	tests = [grep_tests(header), grep_tests(source)].flatten(1)
	if tests.size()
		write_tests base, t_header, t_source, tests
	end
end

last_static_change = [
	File.mtime("update_tests.rb"),
	File.mtime($header_template),
	File.mtime($source_template)
].max()
Dir.foreach("myLisp") { |f|
	if /\.h$/ =~ f
		base = File.basename(f, ".h")
		header = "myLisp/#{base}.h"
		source = "myLisp/#{base}.cpp"

		last_change = [File.mtime(header), File.mtime(source), last_static_change].max()

		t_header = "testLisp/t_#{base}.h"
		t_source = "testLisp/t_#{base}.cpp"
		
		needs_update = false
		if !File.exists?(t_header)
			needs_update = true
		elsif !File.exists?(t_source)
			needs_update = true
		else
			last_update = [File.mtime(t_header), File.mtime(t_source)].min()
			needs_update = last_update < last_change
		end
		
		if needs_update
			update_tests base, header, source, t_header, t_source
		end
	end	
}

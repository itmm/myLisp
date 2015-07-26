#!/usr/bin/ruby

def write_tests(base, t_source, tests)
	File.open(t_source, 'w') do |f|
        tests.each do |test|
            f.write test + "\n"
        end
	end
end

def grep_tests(file)
	tests = []
	in_tests = false
	preset = ''
	File.open(file).each do |line|
		if /\/\*TESTS:/ =~ line
		    in_tests = true
		    preset = ''
		elsif /\*\// =~ line
			in_tests = false
        elsif in_tests && /^\s*\*>/ =~ line
            tests << line.gsub(/^\s*\*>\s*/, "")
        elsif in_tests && /^\s*\*\+/ =~ line
            p = line.gsub(/^\s*\*\+\s*/, "").chomp
            preset += p
		elsif in_tests && /^\s*\*\s/ =~ line
			test = line.gsub(/^\s*\*\s*/, "").gsub(/\n/, '')
			if test != ""
				tests << "((fn () #{preset} #{test}))";
			end
		end
	end
	return tests
end

def update_tests(base, header, source, t_source)
	puts 'testing ' + base + '.lsp'
	tests = [grep_tests(header), grep_tests(source)].flatten(1)
	if tests.size() > 0
		write_tests base, t_source, tests
	end
end

def needs_update(path, last_change)
    result = false
    if ! File.exists? path
        result = true
    else
        last_update = File.mtime(path)
        result = last_update <= last_change
    end
    result
end

last_static_change = File.mtime("update_tests.rb")
Dir.foreach("myLisp") { |f|
	if /\.h$/ =~ f
		base = File.basename(f, ".h")
		header = "myLisp/#{base}.h"
		source = "myLisp/#{base}.cpp"

		last_change = [File.mtime(header), File.mtime(source), last_static_change].max()

        t_source = "tests/t_#{base}.lsp"
		
        if needs_update t_source, last_change
            update_tests base, header, source, t_source
        end
	end
}

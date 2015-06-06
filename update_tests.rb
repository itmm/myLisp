#!/usr/bin/ruby

$source_template = "testLisp/t_template.cpp"

def write_tests(base, t_source, tests)
	File.open(t_source, 'w') do |f|
		File.open($source_template).each do |line|
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

def grep_tests(file, base)
	tests = []
	in_tests = false
    cnt = 1
	File.open(file).each do |line|
		if /\/\*TESTS:/ =~ line
			in_tests = true
		elsif /\*\// =~ line
			in_tests = false
        elsif in_tests && /^\s*\*>/ =~ line
            tests << line.gsub(/^\s*\*>\s*/, "")
		elsif in_tests
			test = line.gsub(/^\s*\*\s*/, "").gsub(/\n/, '')
			if test != ""
                test = "assert(#{test});"
                if /OUT/ =~ test
                    test = "OutSink OUT; #{test}"
                end
				tests << "static void test_#{cnt}() { #{test}; }"
                cnt += 1;
			end
		end
	end
    if cnt > 1
        tests << "class TestInit#{base} { public: TestInit#{base}(); };"
        tests << "static TestInit#{base} testInit#{base};"
        tests << "TestInit#{base}::TestInit#{base}() {";
        for i in (1 .. (cnt-1)) do
            tests << "  all_tests().push_back(test_#{i});"
        end
        tests << "};"
    end
	return tests
end

def update_tests(base, header, source, t_source)
	puts "testing " + header
	tests = [grep_tests(header, "#{base}Header"), grep_tests(source, "#{base}Source")].flatten(1)
	if tests.size() > 0
		write_tests base, t_source, tests
	end
end

last_static_change = [
	File.mtime("update_tests.rb"),
	File.mtime($source_template)
].max()
Dir.foreach("myLisp") { |f|
	if /\.h$/ =~ f
		base = File.basename(f, ".h")
		header = "myLisp/#{base}.h"
		source = "myLisp/#{base}.cpp"

		last_change = [File.mtime(header), File.mtime(source), last_static_change].max()

		t_source = "testLisp/t_#{base}.cpp"
		
		needs_update = false
		if !File.exists?(t_source)
			needs_update = true
		else
			last_update = File.mtime(t_source)
			needs_update = last_update < last_change
		end
		
		if needs_update
			update_tests base, header, source, t_source
		end
	end	
}

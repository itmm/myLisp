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

def grep_tests_cpp(file, base)
	tests = []
	in_tests = false
	preset = ''
    cnt = 1
	File.open(file).each do |line|
		if /\/\*C\+\+-TESTS:/ =~ line
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
                test = "#{preset} assert(#{test});"
				tests << "static void test_#{cnt}() { #{test} }"
                cnt += 1;
			end
		end
	end
    if cnt > 1
        bigBase = base[0].capitalize + base[1..-1]
        tests << "class TestInit#{bigBase} { public: TestInit#{bigBase}(); };"
        tests << "static TestInit#{bigBase} testInit#{bigBase};"
        tests << "TestInit#{bigBase}::TestInit#{bigBase}() {";
        for i in (1 .. (cnt-1)) do
            tests << "  all_tests().push_back(test_#{i});"
        end
        tests << "};"
    end
	return tests
end

def grep_tests_lsp(file, base)
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

def update_tests_lsp(base, header, source, t_source)
	puts 'testing ' + base + '.lsp'
	tests = [grep_tests_lsp(header, "#{base}HeaderLsp"), grep_tests_lsp(source, "#{base}SourceLsp")].flatten(1)
	if tests.size() > 0
		write_tests base, t_source, tests
	end
end

def update_tests_cpp(base, header, source, t_source)
	puts 'testing ' + base + '.cpp'
	tests = [grep_tests_cpp(header, "#{base}Header"), grep_tests_cpp(source, "#{base}Source")].flatten(1)
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

		t_source_cpp = "testLisp/t_#{base}.cpp"
        t_source_lsp = "testLisp/t_#{base}.lsp"
		
        if needs_update t_source_cpp, last_change
            update_tests_cpp base, header, source, t_source_cpp
        end
        if needs_update t_source_lsp, last_change
            update_tests_lsp base, header, source, t_source_lsp
        end
	end
}

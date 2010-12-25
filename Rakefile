require 'rake'
require 'rake/testtask'
require 'rake/rdoctask'
require 'rubygems'
require 'spec/rake/spectask'

task :default => :spec

OBJ = 'ext/llrb.' + Config::CONFIG['DLEXT']

desc "Build llrb extensions"
task :build => OBJ

file OBJ => %w(ext/Makefile) + FileList["ext/*.{cpp,c,h}"] do
  Dir.chdir('ext') { sh 'make' }
end

file "ext/Makefile" => %w(ext/extconf.rb) do
  Dir.chdir('ext') { ruby('extconf.rb') }
end

desc "Remove compiled files"
task :clean do |t|
  for file in FileList.new("ext/*.o", "ext/Makefile", "ext/mkmf.log", OBJ)
    File.delete(file) rescue true
  end
end

desc "Run all specs in spec directory"
Spec::Rake::SpecTask.new do |t|
  t.spec_files = FileList['spec/**/*_spec.rb']
  t.libs << 'ext'
  t.libs << 'spec'
  # Rake::Task[:compile].invoke
end

task :spec => :build

#borrow from http://dev.rubyonrails.org/svn/rails/trunk/railties/lib/code_statistics.rb
#borrow from http://refactormycode.com/codes/91-rake-stats-for-rspec
class SpecStatistics
  TEST_TYPES = ["Specs"]

  def initialize(*pairs)
    @pairs = pairs
    @statistics = calculate_statistics
    @total = calculate_total if pairs.length > 1
  end

  def to_s
    print_header
    @pairs.each { |pair| print_line(pair.first, @statistics[pair.first]) }
    print_splitter

    if @total
      print_line("Total", @total)
      print_splitter
    end

    print_code_test_stats
  end

  private
  def calculate_statistics
    @pairs.inject({}) { |stats, pair| stats[pair.first] = calculate_directory_statistics(pair.last); stats }
  end
  
  def calculate_directory_statistics(directory, pattern = /.*\.rb$/)
    stats = { "lines" => 0, "codelines" => 0, "classes" => 0, "methods" => 0, "specs" => 0, "behaviors" => 0 }


    Dir.foreach(directory) do |file_name|
      if File.stat(directory + "/" + file_name).directory? and (/^\./ !~ file_name)
        newstats = calculate_directory_statistics(directory + "/" + file_name, pattern)
        stats.each { |k, v| stats[k] += newstats[k] }
      end

      next unless file_name =~ pattern

      f = File.open(directory + "/" + file_name)

      while line = f.gets
        stats["lines"] += 1
        stats["classes"] += 1 if line =~ /class [A-Z]/
        stats["methods"] += 1 if line =~ /def [a-z]/
        stats["specs"] += 1 if line.strip =~ /^it.*(do|\{)$/
        stats["behaviors"] += 1 if line =~ /describe.*(do|\{)$/
        stats["codelines"] += 1 unless line =~ /^\s*$/ || line =~ /^\s*#/
      end
    end

    stats
  end

  def calculate_total
    total = { "lines" => 0, "codelines" => 0, "classes" => 0, "methods" => 0, "specs" => 0, "behaviors" => 0 }
    @statistics.each_value { |pair| pair.each { |k, v| total[k] += v } }
    total
  end

  def calculate_code
    code_loc = 0
    @statistics.each { |k, v| code_loc += v['codelines'] unless TEST_TYPES.include? k }
    code_loc
  end

  def calculate_tests
    test_loc = 0
    @statistics.each { |k, v| test_loc += v['codelines'] if TEST_TYPES.include? k }
    test_loc
  end

  def print_header
    print_splitter
    puts "| Name | Lines | LOC | Classes | Methods | Behaviors | Specifications | M/C | LOC/M | S/B |"
    print_splitter
  end

  def print_splitter
    puts "+----------------------+-------+-------+---------+---------+-----------+----------------+-----+-------+-----+"
  end

  def print_line(name, statistics)
    m_over_c = (statistics["methods"] / statistics["classes"]) rescue m_over_c = 0
    loc_over_m = (statistics["codelines"] / statistics["methods"]) - 2 rescue loc_over_m = 0
    
    s_over_b = (statistics["specs"] / statistics["behaviors"]) rescue 0
    
    start = if TEST_TYPES.include? name
      "| #{name.ljust(20)} "
    else
      "| #{name.ljust(20)} "
    end

    puts start +
      "| #{statistics["lines"].to_s.rjust(5)} " +
      "| #{statistics["codelines"].to_s.rjust(5)} " +
      "| #{statistics["classes"].to_s.rjust(7)} " +
      "| #{statistics["methods"].to_s.rjust(7)} " +
      "| #{statistics["behaviors"].to_s.rjust(10)}" +
      "| #{statistics["specs"].to_s.rjust(15)}" +
      "| #{m_over_c.to_s.rjust(3)} " +
      "| #{loc_over_m.to_s.rjust(6)}" +
      "| #{s_over_b.to_s.rjust(3)} |"
  end

  def print_code_test_stats
    code = calculate_code
    tests = calculate_tests

    puts " Code LOC: #{code} Test LOC: #{tests} Code to Test Ratio: 1:#{sprintf("%.1f", tests.to_f/code)}"
    puts ""
  end
end

namespace :spec do
  desc "Report code statistics on the application and specs code"
  task :stats do
    stats_directories = {
      "Specs" => "spec",
      "Application" => "lib"
    }.map {|name, dir| [name, "#{Dir.pwd}/#{dir}"]}
    SpecStatistics.new(*stats_directories).to_s
  end
end
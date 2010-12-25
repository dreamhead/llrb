require 'mkmf'

extension_name = 'llrb'

dir_config(extension_name)
dir_config('llvm', `llvm-config --includedir`.strip, `llvm-config --libdir`.strip)
have_library('stdc++')
have_library('pthread')

components = `llvm-config --libs all`.strip
components = components.split(/\s+/).reject { |lib| lib =~ /LLVMCBase/ }.join(' ')

with_cppflags(`llvm-config --cxxflags`.strip) do
  with_ldflags([`llvm-config --ldflags`.strip, components].join(' ').strip) do
    create_makefile(extension_name)
  end
end
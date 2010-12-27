require 'spec_helper'

describe LLRB do
  it 'should define module' do
    context = get_global_context
    m = LLRB::Module.new('test', context)
    type = LLRB::Type.int32(context)
  end
end
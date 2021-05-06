class Api::Channel::BaseException < Api::BaseException
  def initialize(channel)
    @channel = channel
  end
end

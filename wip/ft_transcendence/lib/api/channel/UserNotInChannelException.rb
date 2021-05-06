class Api::Channel::UserNotInChannelException < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "user not in channel"
  end

  def status()
    return :conflict
  end
end

class Api::Channel::TargetUserNotInChannelException < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "target user not in channel"
  end

  def status()
    return :conflict
  end
end

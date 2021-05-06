class Api::Channel::UserAlreadyInChannelException < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "user already in channel"
  end

  def status()
    return :conflict
  end
end

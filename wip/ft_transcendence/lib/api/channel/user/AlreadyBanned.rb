class Api::Channel::User::AlreadyBanned < Api::Channel::User::BaseException
  def initialize(channel, user)
    super(channel, user)
  end

  def message()
    return "already banned"
  end

  def status()
    return :conflict
  end
end

class Api::Channel::User::NotBanned < Api::Channel::User::BaseException
  def initialize(channel, user)
    super(channel, user)
  end

  def message()
    return "not banned"
  end

  def status()
    return :conflict
  end
end

class Api::Channel::User::NotAnAdministrator < Api::Channel::User::BaseException
  def initialize(channel, user)
    super(channel, user)
  end

  def message()
    return "not an administrator"
  end

  def status()
    return :conflict
  end
end

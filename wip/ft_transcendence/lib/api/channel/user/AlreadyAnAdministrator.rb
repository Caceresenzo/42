class Api::Channel::User::AlreadyAnAdministrator < Api::Channel::User::BaseException
  def initialize(channel, user)
    super(channel, user)
  end

  def message()
    return "already an administrator"
  end

  def status()
    return :conflict
  end
end

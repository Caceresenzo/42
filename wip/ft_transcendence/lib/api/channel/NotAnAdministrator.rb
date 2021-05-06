class Api::Channel::NotAnAdministrator < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "not an administrator"
  end

  def status()
    return :forbidden
  end
end

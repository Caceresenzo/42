class Api::Channel::OwnerCannotLeave < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "owner cannot leave"
  end

  def status()
    return :forbidden
  end
end

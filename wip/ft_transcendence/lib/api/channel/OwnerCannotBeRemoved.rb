class Api::Channel::OwnerCannotBeRemoved < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "owner cannot be removed"
  end

  def status()
    return :forbidden
  end
end

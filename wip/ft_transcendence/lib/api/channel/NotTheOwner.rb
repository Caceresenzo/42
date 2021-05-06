class Api::Channel::NotTheOwner < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "not the owner"
  end

  def status()
    return :forbidden
  end
end

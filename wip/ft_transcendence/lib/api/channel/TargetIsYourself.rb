class Api::Channel::TargetIsYourself < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "target is yourself"
  end

  def status()
    return :forbidden
  end
end

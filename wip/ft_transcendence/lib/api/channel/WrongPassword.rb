class Api::Channel::WrongPassword < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "wrong password"
  end

  def status()
    return :forbidden
  end
end

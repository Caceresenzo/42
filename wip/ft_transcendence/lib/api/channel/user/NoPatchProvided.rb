class Api::Channel::User::NoPatchProvided < Api::Channel::User::BaseException
  def initialize(channel, user)
    super(channel, user)
  end

  def message()
    return "no patch provided"
  end

  def status()
    return :not_acceptable
  end
end

class Api::Channel::User::TooManyPatchProvided < Api::Channel::User::BaseException
  def initialize(channel, user)
    super(channel, user)
  end

  def message()
    return "too many patch provided"
  end

  def status()
    return :not_acceptable
  end
end

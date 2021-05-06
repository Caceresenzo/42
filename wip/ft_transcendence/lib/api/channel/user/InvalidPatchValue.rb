class Api::Channel::User::InvalidPatchValue < Api::Channel::User::BaseException
  def initialize(channel, user)
    super(channel, user)
  end

  def message()
    return "invalid patch value"
  end

  def status()
    return :not_acceptable
  end
end

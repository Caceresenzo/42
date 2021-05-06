class Api::Auth::OtpRequired < Api::Auth::BaseException
  def initialize()
    super()
  end

  def message()
    return "otp required"
  end

  def status()
    return :precondition_failed
  end
end

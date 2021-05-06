class Api::Friendship::CannotRequestToSelf < Api::Friendship::BaseException
  def initialize(user)
    super(user)
  end

  def message()
    return "cannot request to yourself"
  end

  def status()
    return :precondition_failed
  end
end

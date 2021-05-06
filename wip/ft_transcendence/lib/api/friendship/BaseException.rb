class Api::Friendship::BaseException < Api::BaseException
  def initialize(user)
    super()

    @user = user
  end
end

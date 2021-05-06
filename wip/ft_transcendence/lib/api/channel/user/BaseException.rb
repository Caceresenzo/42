class Api::Channel::User::BaseException < Api::BaseException
  def initialize(channel, user)
    @channel = channel
    @user = user
  end
end

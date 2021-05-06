module ChannelUserHelper
  def self.get_for(channel, user)
    ChannelUser.where(
      channel: channel,
      user: user,
    )
  end
end

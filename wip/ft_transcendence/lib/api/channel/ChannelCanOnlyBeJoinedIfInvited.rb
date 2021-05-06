class Api::Channel::ChannelCanOnlyBeJoinedIfInvited < Api::Channel::BaseException
  def initialize(channel)
    super(channel)
  end

  def message()
    return "channel can only be joined if invited"
  end

  def status()
    return :forbidden
  end
end

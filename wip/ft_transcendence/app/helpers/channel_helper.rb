module ChannelHelper
  def self.can_user_show(channel, user)
    channel_user = ChannelUserHelper.get_for(channel, user).take
    is_member = channel_user != nil

    if is_member && channel_user.banned?
      raise CanCan::AccessDenied.new("banned")
    end

    if channel.is_public?
      return true
    end

    if is_member
      return true
    end

    if channel.is_protected?
      raise CanCan::AccessDenied.new("password protected")
    else
      raise CanCan::AccessDenied.new("private")
    end
  end
end

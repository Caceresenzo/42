class ChannelChannel < ApplicationCable::Channel
  def subscribed
    load_entities()

    reject() unless is_accepted(current_user)

    stream_for(@channel)
  end

  private

  def load_entities()
    @channel = Channel.find(params[:channel_id])
  end

  def is_accepted(user)
    return true if user.admin?

    @channel_user = ChannelUser.find_by(
      user: current_user,
      channel: @channel,
    )

    if @channel_user.blank?
      return false unless @channel.is_public?
    else
      return false if @channel_user.banned?
    end

    return true
  end

  def self.broadcast_message(channel, message)
    broadcast_event(channel, :message, ChannelMessageBlueprint.render_as_hash(
      message,
      view: :user,
    ))
  end

  def self.broadcast_member_join(channel, member)
    broadcast_member_action(channel, :join, member)
  end

  def self.broadcast_member_leave(channel, member)
    broadcast_member_action(channel, :leave, member)
  end

  def self.broadcast_member_update(channel, member)
    broadcast_member_action(channel, :update, member)
  end

  def self.broadcast_clear(channel)
    broadcast_event(channel, :clear, nil)
  end

  def self.broadcast_delete(channel)
    broadcast_event(channel, :delete, nil)
  end

  def self.broadcast_member_action(channel, action, member)
    broadcast_event(channel, "member.#{action}", ChannelMemberBlueprint.render_as_hash(
      member
    ))
  end

  def self.broadcast_event(channel, event, item)
    ChannelChannel.broadcast_to(
      channel,
      {
        event: event,
        item: item,
      }
    )
  end
end

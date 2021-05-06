class ChannelUserController < ApplicationController
  before_action :load_entities

  # GET /channels/<channel_id>/members
  def all()
    render({
      json: ChannelMemberBlueprint.render(
        @channel.members.includes(:user)
      ),
    })
  end

  # GET /channels/<channel_id>/members/<user_id>
  def get()
    load_entities(true)
    load_channel_user()

    render({
      json: ChannelMemberBlueprint.render(channel_user),
    })
  end

  # PATCH /channels/<channel_id>/members/<user_id>
  def patch()
    load_entities(true)
    load_channel_user()

    args = params.permit(:banned, :mute_duration, :administrator).to_h()

    raise Api::Channel::User::NoPatchProvided.new(@channel, @user) if args.length == 0
    raise Api::Channel::User::TooManyPatchProvided.new(@channel, @user) if args.length != 1

    if args.key?(:banned)
      value = args[:banned]

      raise Api::Channel::User::InvalidPatchValue.new(@channel, @user) if value != true and value != false

      if @channel_user.banned == value
        raise Api::Channel::User::NotBanned.new(@channel, @user) if !value
        raise Api::Channel::User::AlreadyBanned.new(@channel, @user) if value
      end

      @channel_user.banned = value
      @channel_user.save!()

      # TODO Broadcast event
    elsif args.key?(:administrator)
      value = args[:administrator]

      @channel.is_owner!(current_user)

      raise Api::Channel::User::InvalidPatchValue.new(@channel, @user) if value != true and value != false

      if @channel_user.admin == value
        raise Api::Channel::User::NotAnAdministrator.new(@channel, @user) if !value
        raise Api::Channel::User::AlreadyAnAdministrator.new(@channel, @user) if value
      end

      @channel_user.admin = value
      @channel_user.save!()

      # TODO Broadcast event
    elsif args.key?(:mute_duration)
      value = args[:mute_duration]
      # TODO Broadcast event
    else
      raise StandardError.new("unexpected patch key")
    end

    ChannelChannel.broadcast_member_update(@channel, @channel_user)

    render({
      json: ChannelMemberBlueprint.render(@channel_user),
    })
  end

  # POST /channels/<channel_id>/members
  def add()
    load_entities(true)

    @channel.is_owner!(current_user)

    if ChannelUser.exists?(user: @user, channel: @channel)
      raise Api::Channel::UserAlreadyInChannelException.new(@channel)
    end

    @channel_user = ChannelUser.create!(
      user: @user,
      channel: @channel,
    )

    ChannelChannel.broadcast_member_join(@channel, @channel_user)

    render({
      json: ChannelMemberBlueprint.render(@channel_user),
    })
  end

  # DELETE /channels/<channel_id>/members/<user_id>
  def remove()
    load_entities(true)

    @channel.is_owner!(current_user)

    if current_user == @user
      raise Api::Channel::OwnerCannotBeRemoved.new(@channel)
    end

    load_channel_user()

    @channel_user.destroy()

    ChannelChannel.broadcast_member_leave(@channel, @channel_user)

    render({
      json: ChannelMemberBlueprint.render(@channel_user),
    })
  end

  private

  def load_entities(with_user = false)
    @channel = Channel.find(params[:channel_id])

    if (with_user)
      @user = User.find(params[:user_id])
    end
  end

  def load_channel_user()
    @channel_user = ChannelUser.find_by(
      user: @user,
      channel: @channel,
    )

    if @channel_user.blank?
      raise Api::Channel::UserNotInChannelException.new(@channel)
    end
  end
end

class ChannelMemberUserBlueprint < Blueprinter::Base
  identifier :id

  fields :username
end

class ChannelMemberBlueprint < Blueprinter::Base
  fields :banned, :admin, :muted
  association :user, blueprint: ChannelMemberUserBlueprint
end

class ChannelController < ApplicationController
  authorize_resource

  # GET /channels
  def all()
    render({
      json: ChannelBlueprint.render(Channel.includes(:owner)),
    })
  end

  # GET /channels/<id>
  def show()
    load_entities

    authorize! :show, @channel

    render({
      json: ChannelBlueprint.render(
        @channel,
        view: :members,
      ),
    })
  end

  # POST /channels
  def create()
    args = permitted_params

    @channel = Channel.create!(
      name: args[:name],
      visibility: args[:visibility],
      password: args[:password],
      owner: current_user,
    )

    begin
      ChannelUser.create!(
        user: current_user,
        channel: @channel,
        admin: true,
      )
    rescue
      @channel.destroy()
      raise
    end

    Achievement.COMMUNITY_STARTER.give(current_user)

    render({
      json: ChannelBlueprint.render(@channel),
      status: :created,
    })
  end

  # POST /channels/<id>
  def update()
    load_entities()

    authorize!(:update, @channel)

    @channel.assign_attributes(permitted_params)
    @channel.save!()

    render({
      json: ChannelBlueprint.render(@channel),
    })
  end

  # DELETE /channels/<id>
  def delete()
    load_entities()

    authorize!(:delete, @channel)

    @channel.destroy!()

    ChannelChannel.broadcast_delete(@channel)

    render({
      json: ChannelOnlyIdBlueprint.render(@channel),
    })
  end

  # POST /channels/<id>/join
  def join()
    load_entities()

    add_user(current_user, true)
  end

  # POST /channels/<id>/leave
  def leave()
    load_entities()

    if current_user == @channel.owner
      raise Api::Channel::OwnerCannotLeave.new(@channel)
    end

    @channel_user = channel_user_of(current_user)

    if not @channel_user
      raise Api::Channel::UserNotInChannelException.new(@channel)
    end

    @channel_user.destroy!()

    ChannelChannel.broadcast_member_leave(@channel, @channel_user)

    render({
      json: ChannelOnlyIdBlueprint.render(@channel),
    })
  end

  # POST /channels/<id>/add/<user_id>
  def add()
    load_entities(true)

    add_user(@user, false)
  end

  # POST /channels/<id>/promote/<user_id>
  def promote()
    load_entities(true)

    set_as_administrator(true)
  end

  # POST /channels/<id>/demote/<user_id>
  def demote()
    load_entities(true)

    set_as_administrator(false)
  end

  # POST /channels/<id>/transfer-ownership/<user_id>
  def transfer_ownership()
    load_entities(true)

    if current_user != @channel.owner
      raise Api::Channel::NotTheOwner.new(@channel)
    end

    current_user_channel = channel_user_of(current_user)

    if not current_user_channel # just to be sure
      raise Api::Channel::UserNotInChannelException.new(@channel)
    end

    target_user_channel = channel_user_of(current_user)

    if not target_user_channel
      raise Api::Channel::TargetUserNotInChannelException.new(@channel)
    end

    @channel.owner = @user
    @channel.save!

    target_user_channel.admin = true
    target_user_channel.save!

    render({
      json: ChannelBlueprint.render(@channel),
    })
  end

  private

  def set_as_administrator(flag)
    current_user_channel = channel_user_of(current_user)

    if not current_user_channel
      raise Api::Channel::UserNotInChannelException.new(@channel)
    end

    if not current_user_channel.admin
      raise Api::Channel::NotAnAdministrator.new(@channel)
    end

    target_user_channel = channel_user_of(@user)

    if not target_user_channel
      raise Api::Channel::TargetUserNotInChannelException.new(@channel)
    end

    if target_user_channel.admin
      raise Api::Channel::AlreadyAnAdministrator.new(@channel)
    end

    target_user_channel.admin = true
    target_user_channel.save!

    render({
      json: ChannelOnlyIdBlueprint.render(@channel),
    })
  end

  def add_user(user, restricted)
    if ChannelUser.exists?(channel: @channel, user: current_user)
      raise Api::Channel::UserAlreadyInChannelException.new(@channel)
    end

    if restricted and @channel.is_private?
      raise Api::Channel::ChannelCanOnlyBeJoinedIfInvited.new(@channel)
    end

    if @channel.is_protected?
      password = params[:password]

      if not @channel.authenticate(password)
        raise Api::Channel::WrongPassword.new(@channel)
      end
    end

    @channel_user = ChannelUser.create!(
      channel: @channel,
      user: current_user,
    )

    ChannelChannel.broadcast_member_join(@channel, @channel_user)

    render({
      json: ChannelOnlyIdBlueprint.render(@channel),
    })
  end

  def load_entities(user_too = false)
    @channel = Channel.find(params[:id])

    if user_too
      params.require(:user_id)
      @user = User.find(params[:user_id])
    else
      @user = nil
    end
  end

  def channel_user_of(user)
    ChannelUser.find_by(
      channel: @channel,
      user: user,
    )
  end

  def permitted_params()
    return params.permit(:name, :visibility, :password)
  end
end

class ChannelOwnerBlueprint < Blueprinter::Base
  identifier :id

  fields :username
end

class ChannelMemberUserBlueprint < Blueprinter::Base
  identifier :id

  fields :username
end

class ChannelMemberBlueprint < Blueprinter::Base
  fields :banned, :admin, :muted
  association :user, blueprint: ChannelMemberUserBlueprint
end

class ChannelBlueprint < Blueprinter::Base
  identifier :id

  fields :name, :owner, :visibility, :updated_at, :created_at
  association :owner, blueprint: ChannelOwnerBlueprint

  view :members do
    association :members, blueprint: ChannelMemberBlueprint
  end
end

class ChannelOnlyIdBlueprint < Blueprinter::Base
  identifier :id
end

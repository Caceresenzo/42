class ChannelMessageController < ApplicationController
  before_action :load_entities

  # GET /channels/<channel_id>/messages
  def all()
    render({
      json: ChannelMessageBlueprint.render(
        @channel.messages.includes(:user),
        view: :user,
      ),
    })
  end

  # POST /channels/<channel_id>/messages
  def create()
    @message = ChannelMessage.create!(
      user: current_user,
      channel: @channel,
      content_type: params[:content_type],
      content: params[:content],
    )

    ChannelChannel.broadcast_message(@channel, @message)

    Achievement.DONT_BE_SHY.give(current_user)
    Achievement.SMALL_TALKER.increment(current_user)

    render({
      json: ChannelMessageBlueprint.render(
        @message
      ),
    })
  end

  # DELETE /channels/<channel_id>/messages
  def clear()
    ChannelMessage.where(channel: @channel).delete_all()

    ChannelChannel.broadcast_clear(@channel)

    render({
      json: ChannelMessageBlueprint.render([]), # empty list
    })
  end

  private

  def load_entities
    @channel = Channel.find(params[:channel_id])
  end
end

class ChannelMessageChannelBlueprint < Blueprinter::Base
  identifier :id

  fields :name
end

class ChannelMessageUserBlueprint < Blueprinter::Base
  identifier :id

  fields :username
end

class ChannelMessageBlueprint < Blueprinter::Base
  identifier :id

  fields :content_type, :content, :updated_at, :created_at

  view :channel do
    association :channel, blueprint: ChannelMessageChannelBlueprint
  end

  view :user do
    association :user, blueprint: ChannelMessageUserBlueprint
  end

  view :extended do
    include_view :channel
    include_view :user
  end
end

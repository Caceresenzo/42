class FriendshipController < ApplicationController

  # GET /users/<user_id>/friends
  def get()
    load_entities(false)

    begin
      x = @user.friends[0]
      puts x
      puts x
    rescue StandardError => e
      print(e)
      print(e.instance_variables)
    end

    render({
      json: FriendshipBlueprint.render(@user.friends, view: :friend),
    })
  end

  # GET /users/<user_id>/friends/pending
  def pending()
    load_entities(false)

    render({
      json: FriendshipBlueprint.render(@user.pending_friends, view: :received_side),
    })
  end

  # GET /users/<user_id>/friends/requests
  def requests()
    load_entities(false)

    render({
      json: FriendshipBlueprint.render(@user.pending_requests, view: :send_side),
    })
  end

  # GET /users/<user_id>/friends/<friend_id>
  def status()
    load_entities(true)

    render({
      json: FriendshipBlueprint.render(@user.pending_requests, view: :normal),
    })
  end

  # POST /users/<user_id>/friends
  def create()
    load_entities(false)

    raise Api::Friendship::CannotRequestToSelf.new(@user) if @user == current_user

    friendship = Friendship.find_by(
      user: current_user,
      friend: @user,
    )

    if friendship.blank?()
      friendship = Friendship.create!(
        user: current_user,
        friend: @user,
        accepted: false,
      )
    end

    render({
      json: FriendshipBlueprint.render(friendship, view: :normal),
    })
  end

  # POST /users/<user_id>/friends/<friend_id>
  def accept()
    load_entities(true)

    @friendship.confirm!()

    render({
      json: FriendshipBlueprint.render(@friendship, view: :normal),
    })
  end

  # DELETE /users/<user_id>/friends/<friend_id>
  def delete()
    load_entities(true)

    @friendship.destroy_model!()

    render({
      json: FriendshipBlueprint.render(@friendship, view: :normal),
    })
  end

  private

  def load_entities(with_friend = false)
    @user = User.find(params[:user_id])

    if with_friend
      @friend = User.find(params[:friend_id])

      @friendship = Friendship.find(
        user: @user,
        friend: @friend,
      )
    end
  end
end

class FriendshipUserBlueprint < Blueprinter::Base
  identifier :id

  fields :username
end

class FriendshipBlueprint < Blueprinter::Base
  fields :accepted

  view :received_side do
    association :user, blueprint: FriendshipUserBlueprint
  end

  view :send_side do
    association :friend, blueprint: FriendshipUserBlueprint
  end

  view :friend do
    association :friend, blueprint: FriendshipUserBlueprint
  end

  view :normal do
    association :user, blueprint: FriendshipUserBlueprint
    include_view :friend
  end
end

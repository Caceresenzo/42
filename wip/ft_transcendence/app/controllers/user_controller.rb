class UserController < ApplicationController
  authorize_resource

  # GET /users/current
  def current()
    render({
      json: UserBlueprint.render(current_user, view: :self),
    })
  end

  # GET /users
  def all()
    render({
      json: UserBlueprint.render(User.all()),
    })
  end

  # GET /users/<id>
  def show()
    load_entities_full()

    render({
      json: UserBlueprint.render(
        @user,
        view: :full,
      ),
    })
  end

  private

  def load_entities()
    @user = User.includes(avatar_attachment: :blob).find(params[:id])
  end

  def load_entities_full()
    @user = User.includes(
      achievement_progress: :achievement,
      avatar_attachment: :blob,
    ).find(params[:id])
  end
end

class UserStatisticsBlueprint < Blueprinter::Base
  fields :win_count, :loss_count
end

class UserAchievementProgressAchievementBlueprint < Blueprinter::Base
  fields :id, :name, :description, :percent, :max
end

class UserAchievementProgressBlueprint < Blueprinter::Base
  fields :value, :unlocked_at
  field :unlocked?, name: :unlocked

  association :achievement, blueprint: UserAchievementProgressAchievementBlueprint
end

class UserBlueprint < Blueprinter::Base
  identifier :id

  fields :username, :email, :picture, :admin, :updated_at, :created_at

  view :full do
    association :statistics, blueprint: UserStatisticsBlueprint
    association :achievement_progress, name: :achievement_progresses, blueprint: UserAchievementProgressBlueprint
  end

  view :self do
    fields :otp_provisioning_uri
  end
end

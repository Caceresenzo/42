class AchievementController < ApplicationController
  def all
    render({
      json: AchievementBlueprint.render(Achievement.all()),
    })
  end
end

class AchievementBlueprint < Blueprinter::Base
  identifier :id

  fields :name, :description, :percent, :max
end

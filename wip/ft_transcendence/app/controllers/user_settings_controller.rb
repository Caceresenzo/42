class UserSettingsController < ApplicationController

  # GET /users/current/settings
  def get()
    render({
      json: UserSettingsBlueprint.render(UserSettings.new(current_user)),
    })
  end

  # POST /users/current/settings
  def update()
    args = params.permit(:username, :otp)

    current_user.assign_attributes(args)
    current_user.save!()

    get()
  end

  def update_image()
    # TODO @badria

    get()
  end
end

class UserSettingsBlueprint < Blueprinter::Base
  fields :username, :otp, :otp_url, :picture
end

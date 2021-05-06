class Users::OmniauthCallbacksController < Devise::OmniauthCallbacksController
  def marvin()
    @user = User.from_omniauth(request.env["omniauth.auth"])

    # puts request.env["omniauth.auth"].as_json

    if @user.persisted?()
      sign_in_and_redirect(@user, :event => :authentication)
      set_flash_message(:notice, :success, :kind => "42") if is_navigational_format?
    else
      session["devise.marvin_data"] = request.env["omniauth.auth"].delete_if { |key, value| key == "extra" }
      redirect_to(new_user_registration_url)
    end
  end

  def google_oauth2()
    @user = User.from_omniauth(request.env["omniauth.auth"])

    # puts request.env["omniauth.auth"].as_json

    if @user.persisted?()
      session[:require_otp] = @user.otp?

      sign_in_and_redirect(@user, :event => :authentication)
      set_flash_message(:notice, :success, :kind => "Google") if is_navigational_format?
    else
      session[:require_otp] = @user.otp?
      session["devise.marvin_data"] = request.env["omniauth.auth"].delete_if { |key, value| key == "extra" }

      redirect_to(new_user_session_url)
    end
  end
end

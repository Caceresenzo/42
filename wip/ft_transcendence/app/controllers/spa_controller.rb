class SpaController < ApplicationController

  # POST /
  def unlock()
    otp_code = params["otp-code"]

    if otp_code and current_user.authenticate_otp(otp_code.to_s())
      session[:require_otp] = false
      redirect_to(root_path)
    else
      flash[:alert] = "invalid code"
      render(:index)
    end
  end

  protected

  def ensure_otp_logged()
    # no operation
  end
end

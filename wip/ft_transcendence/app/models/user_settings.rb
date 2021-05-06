class UserSettings
  def initialize(user)
    @user = user
  end

  def username()
    return @user.username
  end

  def otp()
    return @user.otp
  end

  def otp_url()
    return @user.otp_provisioning_uri()
  end

  def picture()
    return @user.picture()
  end
end

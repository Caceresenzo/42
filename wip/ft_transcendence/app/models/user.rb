class User < ApplicationRecord
  include Rails.application.routes.url_helpers

  has_one_time_password

  after_create :create_statistics
  after_create :give_registered_achivement

  devise(
    :omniauthable,
    omniauth_providers: [
      #TODO MARVIN :marvin,
      :google_oauth2,
    ],
  )

  has_one :statistics, dependent: :destroy, inverse_of: :user, class_name: "UserStatistics"
  has_one_attached :avatar
  has_many :achievement_progress, dependent: :destroy, inverse_of: :user

  has_many :friendships, dependent: :destroy, inverse_of: :user
  has_many :friendships2, dependent: :destroy, inverse_of: :friend

  has_many :friends, -> { where(accepted: true) }, class_name: "Friendship"
  has_many :pending_requests, -> { where(accepted: false) }, class_name: "Friendship"
  has_many :pending_friends, -> { where(accepted: false) }, class_name: "Friendship", foreign_key: :friend_id

  validates :username, uniqueness: true, presence: true
  validates :otp, inclusion: { in: [true, false] }

  def self.from_omniauth(auth)
    where(provider: auth.provider, uid: auth.uid).first_or_create do |user|
      user.email = auth.info.email
      user.username = auth.info.nickname
      user.username ||= auth.info.email.split(/@/, 2)[0]
      user.avatar.attach(io: URI.open(auth.info.image), filename: "#{user.username}.png")
      user.admin = (User.count() == 0) # is first user?
    end
  end

  def picture()
    return rails_blob_path(avatar, only_path: true) if avatar.attached?()
  end

  def otp_provisioning_uri()
    return provisioning_uri(nil, issuer: "ft_transcendence")
  end

  private

  def create_statistics()
    UserStatistics.create!(
      user: self,
    )
  end

  def give_registered_achivement()
    Achievement.REGISTERED.give(self)
  end
end

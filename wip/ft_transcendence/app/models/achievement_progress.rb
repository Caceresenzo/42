class AchievementProgress < ApplicationRecord
  belongs_to :achievement
  belongs_to :user

  def unlocked?
    unlocked_at != nil
  end
end

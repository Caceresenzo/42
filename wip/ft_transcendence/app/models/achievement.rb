class Achievement < ApplicationRecord
  @@REGISTERED = Achievement.new(
    id: 1000,
    name: "Registered",
    description: "Create an account",
    percent: false,
    max: 1,
  )

  @@COMMUNITY_STARTER = Achievement.new(
    id: 2000,
    name: "Community Starter",
    description: "Create a Channel",
    percent: false,
    max: 1,
  )

  @@DONT_BE_SHY = Achievement.new(
    id: 3000,
    name: "Don't be shy",
    description: "Send your first message",
    percent: false,
    max: 1,
  )

  @@SMALL_TALKER = Achievement.new(
    id: 3100,
    name: "Small Talker",
    description: "Send 20 message",
    percent: false,
    max: 20,
  )

  def give(user)
    set(user, max)
  end

  def increment(user, incr = 1)
    progress = get_progress(user)

    if not progress.unlocked?
      progress.value = [max, progress.value + incr].min

      if progress.value == max
        progress.unlocked_at = DateTime.current
      end

      progress.save #!
    end

    progress
  end

  def set(user, value)
    value = [value, max].min
    progress = get_progress(user)

    if progress.value != value
      progress.value = value

      if progress.value != max
        progress.unlocked_at = nil
      elsif progress.unlocked_at == nil
        progress.unlocked_at = DateTime.current
      end

      progress.save #!
    end

    progress
  end

  def get_progress(user)
    AchievementProgress.where(user: user, achievement: self).first_or_create
  end

  cattr_accessor :REGISTERED
  cattr_accessor :COMMUNITY_STARTER
  cattr_accessor :DONT_BE_SHY, :SMALL_TALKER

  def self.create_all()
    save_if_not_exists(@@REGISTERED)
    save_if_not_exists(@@COMMUNITY_STARTER)
    save_if_not_exists(@@DONT_BE_SHY)
    save_if_not_exists(@@SMALL_TALKER)
  end

  private

  def self.save_if_not_exists(achievement)
    if not Achievement.exists?(id: achievement.id)
      achievement.save!
    end
  end
end

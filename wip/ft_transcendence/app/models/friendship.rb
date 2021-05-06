class Friendship < ApplicationRecord
  belongs_to :user, class_name: "User"
  belongs_to :friend, class_name: "User"

  def confirm!()
    return if accepted?

    ActiveRecord::Base.transaction do
      update!(accepted: true)

      Friendship.create!(
        user: friend,
        friend: user,
        accepted: true,
      )
    end
  end

  def destroy_model!()
    ActiveRecord::Base.transaction do
      destroy_other!() if accepted?
      destroy!()
    end
  end

  private

  def destroy_other!()
    Friendship.where(
      user: friend,
      friend: user,
    ).destroy!()
  end

  def cannot_be_self()
    if user == friend
      errors.add(:self, "can't be friend with yourself")
    end
  end
end

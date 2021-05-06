class CreateAchievementProgresses < ActiveRecord::Migration[6.1]
  def change
    create_table :achievement_progresses do |t|
      t.references :achievement, null: false, foreign_key: true
      t.references :user, type: :uuid, null: false, foreign_key: true
      t.integer :value, null: false, default: 0
      t.datetime :unlocked_at

      t.timestamps
    end

	add_index :achievement_progresses, [:achievement_id, :user_id], unique: true
  end
end

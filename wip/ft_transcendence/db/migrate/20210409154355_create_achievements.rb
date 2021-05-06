class CreateAchievements < ActiveRecord::Migration[6.1]
  def change
    create_table :achievements do |t|
      t.string :name, null: false
      t.string :description, null: false
      t.boolean :percent, null: false, default: true
      t.integer :max, null: false, default: 0

      t.timestamps
    end
  end
end

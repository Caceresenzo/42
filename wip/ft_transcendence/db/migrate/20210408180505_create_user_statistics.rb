class CreateUserStatistics < ActiveRecord::Migration[6.1]
  def change
    create_table :user_statistics, id: :uuid do |t|
      t.references :user, type: :uuid, null: false, foreign_key: true
      t.integer :win_count, null: false, default: 0
      t.integer :loss_count, null: false, default: 0

      t.timestamps
    end
  end
end

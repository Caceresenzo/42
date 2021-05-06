class CreateFriendships < ActiveRecord::Migration[6.1]
  def change
    create_table :friendships, id: :uuid do |t|
      t.references :user, null: false, type: :uuid, foreign_key: { to_table: "users" }
      t.references :friend, null: false, type: :uuid, foreign_key: { to_table: "users" }
      t.boolean :accepted, null: false, default: false

      t.timestamps
    end

    add_index :friendships, [:user_id, :friend_id], unique: true
  end
end

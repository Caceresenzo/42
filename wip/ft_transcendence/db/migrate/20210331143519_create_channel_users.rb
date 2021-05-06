class CreateChannelUsers < ActiveRecord::Migration[6.1]
  def change
    create_table :channel_users, id: :uuid do |t|
      t.references :user, type: :uuid, null: false, foreign_key: true
      t.references :channel, type: :uuid, null: false, foreign_key: true
      t.boolean :admin, null: false, default: false
      t.boolean :banned, null: false, default: false
      t.boolean :muted, null: false, default: false
      t.timestamp :muted_until

      t.timestamps
    end

    add_index :channel_users, [:user_id, :channel_id], unique: true
  end
end

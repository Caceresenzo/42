class CreateChannelMessages < ActiveRecord::Migration[6.1]
  def change
    create_table :channel_messages, id: :uuid do |t|
      t.integer :content_type, null: false
      t.text :content, null: false
      t.references :user, type: :uuid, null: false, foreign_key: true
      t.references :channel, type: :uuid, null: false, foreign_key: true

      t.timestamps
    end
  end
end

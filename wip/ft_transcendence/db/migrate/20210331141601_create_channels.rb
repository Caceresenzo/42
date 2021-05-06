class CreateChannels < ActiveRecord::Migration[6.1]
  def change
    create_table :channels, id: :uuid do |t|
      t.string :name, null: true
      t.integer :visibility, null: false
      t.string :password_digest, null: true
      t.references :owner, null: false, type: :uuid, foreign_key: { to_table: "users" }

      t.timestamps
    end
  end
end

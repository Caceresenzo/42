package ft.hangouts.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.LinearLayout;

import ft.hangouts.Constants;
import ft.hangouts.R;
import ft.hangouts.activity.base.TrackedActivity;
import ft.hangouts.model.Contact;
import ft.hangouts.util.ActionBarColorUtil;

public class ContactActivity extends TrackedActivity {

    private Contact mContact;
    private boolean mMessageButton;

    private LayoutGroup mPhoneGroup;
    private LayoutGroup mNameGroup;
    private LayoutGroup mNicknameGroup;
    private LayoutGroup mEmailGroup;
    private LayoutGroup mAddressGroup;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contact);

        mPhoneGroup = new LayoutGroup(R.id.phoneLayout, R.id.phone);
        mNameGroup = new LayoutGroup(R.id.nameLayout, R.id.name);
        mNicknameGroup = new LayoutGroup(R.id.nicknameLayout, R.id.nickname);
        mEmailGroup = new LayoutGroup(R.id.emailLayout, R.id.email);
        mAddressGroup = new LayoutGroup(R.id.addressLayout, R.id.address);

        mContact = (Contact) getIntent().getSerializableExtra(Constants.KEY_CONTACT);
        mMessageButton = getIntent().getBooleanExtra(Constants.KEY_MESSAGE_BUTTON, true);

        if (mContact == null) {
            finish();
            return;
        }

        ActionBarColorUtil.apply(this);

        getActionBar().setDisplayHomeAsUpEnabled(true);

        updateTitle();
        updateGroups();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_contact, menu);

        menu.findItem(R.id.action_message).setVisible(mMessageButton);

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home: {
                finish();

                return true;
            }

            case R.id.action_edit: {
                ContactEditorActivity.start(this, Constants.REQUEST_CODE_CONTACT_ACTIVITY, mContact);

                return true;
            }

            case R.id.action_message: {
                MessagesActivity.start(this, Constants.REQUEST_CODE_CONTACT_ACTIVITY, mContact);

                return true;
            }
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == Constants.REQUEST_CODE_CONTACT_ACTIVITY) {
            switch (resultCode) {
                case Constants.RESULT_CODE_EDITED: {
                    setResult(resultCode, data);

                    mContact = (Contact) data.getSerializableExtra(Constants.KEY_CONTACT);

                    updateTitle();
                    updateGroups();

                    break;
                }

                case Constants.RESULT_CODE_REMOVED: {
                    setResult(resultCode, data);
                    finish();

                    break;
                }
            }

            if (resultCode == Constants.RESULT_CODE_REMOVED) {
                finish();
            }
        }

        super.onActivityResult(requestCode, resultCode, data);
    }

    public void updateTitle() {
        String title = mContact.getDisplayableTitle();
        getActionBar().setTitle(title);
    }

    public void updateGroups() {
        mPhoneGroup.update(mContact.getPhone());
        mNameGroup.update(mContact.getName());
        mNicknameGroup.update(mContact.getNickname());
        mEmailGroup.update(mContact.getEmail());
        mAddressGroup.update(mContact.getAddress());
    }

    public static void start(Activity context, int requestCode, Contact contact, boolean messageButton) {
        Intent intent = new Intent(context, ContactActivity.class);
        intent.putExtra(Constants.KEY_CONTACT, contact);
        intent.putExtra(Constants.KEY_MESSAGE_BUTTON, messageButton);

        context.startActivityForResult(intent, requestCode);
    }

    private class LayoutGroup {

        private final LinearLayout mLinearLayout;
        private final EditText mEditText;

        public LayoutGroup(int linearLayoutId, int editTextId) {
            this.mLinearLayout = findViewById(linearLayoutId);
            this.mEditText = findViewById(editTextId);
        }

        public void update(String value) {
            boolean valid = TextUtils.isEmpty(value);

            mLinearLayout.setVisibility(valid ? View.GONE : View.VISIBLE);
            mEditText.setText(valid ? null : value);
        }
    }
}
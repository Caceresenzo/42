export default {
  language: 'English',
  relationship: {
    tab: {
      online: {
        _: 'online',
        top: 'online',
      },
      friends: {
        _: 'friends',
        top: 'all',
      },
      pending: {
        _: 'pending',
        top: 'pending',
      },
      blocked: {
        _: 'blocked',
        top: 'blocked',
      },
    },
    nothing: 'nothing to see',
  },
  channel: {
    create: {
      _: 'Create a channel',
      action: 'create',
    },
    discover: {
      _: 'Discover some channels',
      action: 'discover',
      unlock: {
        title: 'Unlock channel access {name}',
        label: 'What is the psassword?',
      },
    },
    visibility: {
      public: 'Public',
      protected: 'Protected',
      private: 'Private',
    },
    group: {
      owner: 'Owner',
      admin: 'Admin',
      user: 'User',
      banned: 'Banned',
    },
    field: {
      name: {
        _: 'Name',
      },
      visibility: {
        _: 'Visibility',
      },
      password: {
        _: 'Password',
        'leave-empty': 'Leave empty to not modify',
      },
    },
    settings: {
      title: 'Settings of {name}',
      button: 'settings',
      danger: {
        title: 'Danger Zone',
        actions: {
          'clear-messages': {
            _: 'Clear Messages',
            confirm: 'This will remove all of the messages.',
          },
          'delete-channel': {
            _: 'Delete Channel',
            confirm:
              'This will remove the channel as well as all of its messages',
          },
        },
      },
    },
    invite: {
      title: 'Invite people to {name}',
      label: 'What is his username?',
      button: 'invite',
    },
    leave: {
      title: 'Leave channel {name}?',
      button: 'leave',
    },
    join: {
      button: 'join',
    },
    mute: {
      title: 'Mute {user}',
      button: 'mute',
      durations: {
        '5m': '5 minutes',
        '15m': '15 minutes',
        '1h': '1 hour',
        '12h': '12 hours',
        '1d': '1 day',
        '10d': '10 days',
        '1M': '1 month',
        '1Y': '1 year',
        indefinitely: 'indefinitely',
      },
    },
    action: {
      transfer:
        'Are you sure that you want to transfer the ownership of this channel to {user}?',
      promote: 'Are you sure that you want to promote {user}?',
      demote: 'Are you sure that you want to demote {user}?',
      ban: 'Are you sure that you want to ban {user}?',
      unban: 'Are you sure that you want to unban {user}?',
      kick: 'Are you sure that you want to kick {user}?',
      unmute: 'Are you sure that you want to unmute {user}?',
    },
  },
  error: {
    retry: 'retry',
  },
}

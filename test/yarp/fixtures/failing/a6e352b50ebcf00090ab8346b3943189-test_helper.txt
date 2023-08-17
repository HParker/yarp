module Jingubang
  module Test
    module TestHelper

      def build_qiye_weixin_test_notification echostr, encryptor
        encrypted_payload, timestamp, nonce, signature = encryptor.encrypt_with_signature(echostr)

        {
          'echostr' => encrypted_payload,
          'msg_signature' => signature,
          'timestamp' => timestamp,
          'nonce' => nonce
        }
      end

      def build_qiye_weixin_notification message, encryptor
        encrypted_payload, timestamp, nonce, signature = encryptor.encrypt_with_signature(message)

        {
          'xml' => {
            'ToUserName' => 'testusername',
            'Encrypt' => encrypted_payload
          },
          'msg_signature' => signature,
          'timestamp' => timestamp,
          'nonce' => nonce
        }
      end

      class ApiResult

        class << self

          def build_weixin_qiye_login_info corpid: 'thecorpid', userid: 'theuserid', error_code: nil
            return build_weixin_qiye_error_result(error_code) if error_code
            {
              usertype: 1,
              user_info: {
                userid:  userid,
                name: 'User Name',
                email: 'user@test.com',
                avatar: 'http://p.qlogo.cn/bizmail/thelinktouseravatar/0'
              },
              corp_info: {
                corpid: corpid
              },
              agent: [
                {agentid: 1000010, auth_type: 1},
                {agentid: 1000029, auth_type: 1}
              ],
              auth_info: {
                department: [
                  {id: 1, writable: true}
                ]
              }
            }
          end

          def build_weixin_qiye_permanent_auth_data mobile: '13812345678', email: 'anna@frozen.com'
            {
              access_token: 'ACCESS_TOKEN',
              expires_in: 7200,
              permanent_code: 'PERMANENT_CODE',
              auth_corp_info: {
                corpid: 'WXCORPID',
                corp_name: 'Frozen Tech',
                corp_type: 'unverified',
                corp_round_logo_url: 'http://mmbiz.qpic.cn/mmbiz/round_logo/0',
                corp_square_logo_url: 'http://p.qpic.cn/qqmail_pic/4144698419/square_logo/0',
                corp_user_max: 200,
                corp_agent_max: 0,
                corp_wxqrcode: 'http://shp.qpic.cn/bizmp/wxqrcode/',
                corp_full_name: '',
                subject_type: 1,
                verified_end_time: 0
              },
              auth_info: {
                agent: [{
                  agentid: 1000005,
                  name: '金数据DEV',
                  square_logo_url: 'http://p.qlogo.cn/bizmail/agent_square_logo/0',
                  appid: 1,
                  privilege: {
                    level: 2,
                    allow_party: [1],
                    allow_user: [],
                    allow_tag: [],
                    extra_party: [],
                    extra_user: [],
                    extra_tag: []
                  }
                }]
              },
              auth_user_info: {
                userid: 'anna',
                mobile: mobile,
                email: email,
                name: 'Anna',
                avatar: 'http://p.qlogo.cn/bizmail/anna_avatar/0'
              }
            }.with_indifferent_access
          end

          private

          def build_weixin_qiye_error_result error_code
            {
              errcode: error_code,
              errmsg: 'invalid code, hint: [1519698145_8_22f41dcc18e2ca451dd57b93b129b35d], more info at https://open.work.weixin.qq.com/devtool/query?e=40029',
              agent: []
            }
          end

        end
      end

    end
  end
end

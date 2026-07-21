/*
 * FileName:     Easing.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/21
 *
 * イージング
 */

#pragma once

namespace Libraries
{
	namespace Easing
	{
		// 補間方法
		enum class Type
		{
			Linear,
			Sine,
			Quad,
			Cubic,
			Quart,
			Quint,
			Expo,
			Circ,
			Back,
			Elastic,
			Bounce,
		};

		// イーズインアウト
		enum class InOut
		{
			In,
			Out,
			InOut,
			OutIn,
		};

		// イージング
		template<typename T> requires IsSame
		<
			T,
			float,
			Math::Vector2,
			Math::Vector3,
			Math::Matrix,
			Math::Quaternion,
			Math::Euler,
			Camera::QuaternionCamera,
			Camera::QuaternionTargetCamera,
			Camera::EulerCamera,
			Camera::EulerTargetCamera
		>
		class Value
		{

		public:


			/* メンバ関数 */

			// コンストラクタ
			Value()
				: m_begin{}
				, m_end{}
				, m_timer{}
				, m_type{}
				, m_inOut{}
			{
			}

			// 更新処理
			void Tick(float elapsedTime) { m_timer += elapsedTime; }

			// 初期値を設定
			void SetMovement(const T& begin, const T& end, float time, Type type = Type::Linear, InOut inOut = InOut::In)
			{
				m_begin = begin;
				m_end = end;
				m_timer.Initialize(0.0f, 0.0f, time);
				m_type = type;
				m_inOut = inOut;
			}
			// 初期値を設定
			void SetMovement(const T& value, float time, Type type = Type::Linear, InOut inOut = InOut::In)
			{
				m_begin = GetMovement();
				m_end = value;
				m_timer.Initialize(0.0f, 0.0f, time);
				m_type = type;
				m_inOut = inOut;
			}

			// 現在の値を取得
			T GetMovement() const
			{
				// 時間経過率
				float t = m_timer.GetRatio();
				// 移動率
				float s;
				switch (m_inOut)
				{
				case InOut::In:
					s = EasingFunction(t, m_type);
					break;
				case InOut::Out:
					s = 1.0f - EasingFunction(1.0f - t, m_type);
					break;
				case InOut::InOut:
					s = t < 0.5f ? 0.5f * EasingFunction(2.0f * t, m_type) : 1.0f - 0.5f * EasingFunction(2.0f - 2.0f * t, m_type);
					break;
				case InOut::OutIn:
					s = t < 0.5f ? 0.5f - 0.5f * EasingFunction(1.0f - 2.0f * t, m_type) : 0.5f + 0.5f * EasingFunction(2.0f * t - 1.0f, m_type);
					break;
				default:
					s = t;
					break;
				};

				// 移動率をもとに線形補間
				return Lerp(m_begin, m_end, s);
			}

			// 移動中かどうか
			bool IsMoving() const { return !m_timer.IsMax(); }


		private:


			/* メンバ関数 */

			// イージング
			float EasingFunction(float t, Type type) const
			{
				switch (type)
				{
				case Type::Linear:
					return t;
				case Type::Sine:
					return 1.0f - Math::Cos(Math::PI * t / 2.0f);
				case Type::Quad:
					return t * t;
				case Type::Cubic:
					return t * t * t;
				case Type::Quart:
					return t * t * t * t;
				case Type::Quint:
					return t * t * t * t * t;
				case Type::Expo:
					return (Math::Exp(7.0f * t) - 7.0f * t - 1.0f) / (Math::Exp(7.0f) - 8.0f);
				case Type::Circ:
					return 1.0f - Math::Sqrt(1.0f - t * t);
				case Type::Back:
					return 3.0f * t * t * t - 2.0f * t * t;
				case Type::Elastic:
					return t * t * t * t * Math::Cos(4.0f * Math::PI * t);
				case Type::Bounce:
					return Math::Abs(t * Math::Sqrt(t) * Math::Cos(4.0f * Math::PI * Math::Sqrt(t)));
				default:
					return t;
				}
			}

			// 線形補間
			static T Lerp(const T& x, const T& y, float t) { return T::Lerp(x, y, t); }


			/* メンバ変数 */

			// 開始値
			T m_begin;
			// 終了値
			T m_end;

			// 移動時間	[s]
			Limited m_timer;

			// 補完方法
			Type  m_type;
			// イーズインアウト
			InOut m_inOut;

		};

		// 線形補間
		template<>
		inline static float Value<float>::Lerp(const float& x, const float& y, float t) { return Math::Lerp(x, y, t); }
	}
}

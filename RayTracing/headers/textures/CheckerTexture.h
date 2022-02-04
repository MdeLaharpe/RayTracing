#ifndef RT_CHECKER_H
#define RT_CHECKER_H

#include "textures/Texture.h"

#include "maths/Utils.h"
#include "textures/SolidColorTexture.h"

namespace rt
{
	class CheckerTexture : public Texture
	{
	public:
		CheckerTexture()
			: evenTexture(std::make_shared<SolidColorTexture>()), oddTexture(std::make_shared<SolidColorTexture>(maths::Vec3{ 1.f })), piOverScale(maths::pi)
		{ }
		CheckerTexture(const maths::Vec3& evenColor, const maths::Vec3& oddColor, float scale)
			: evenTexture(std::make_shared<SolidColorTexture>(evenColor)), oddTexture(std::make_shared<SolidColorTexture>(oddColor)), piOverScale(maths::pi / scale)
		{ }
		CheckerTexture(std::shared_ptr<Texture> evenTexture, std::shared_ptr<Texture> oddTexture, float scale)
			: evenTexture(std::move(evenTexture)), oddTexture(std::move(oddTexture)), piOverScale(maths::pi / scale)
		{ }

		virtual ~CheckerTexture() { }

		virtual maths::Vec3 Value(float u, float v, const maths::Vec3& point) const override;

	private:
		std::shared_ptr<Texture> evenTexture, oddTexture;
		float piOverScale;
	};
}

#endif RT_CHECKER_H
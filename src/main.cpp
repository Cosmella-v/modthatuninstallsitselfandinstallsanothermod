#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
using namespace geode::prelude;


static async::TaskHolder<web::WebResponse> t;

$on_mod(Loaded) {
	geode::Loader::get()->queueInMainThread([] {
		t.spawn(
			web::WebRequest().get("https://github.com/slideglide/modthatclosesthegamewhenitopenshelper-geode/releases/latest/download/slideglide.modthatclosesthegamewhenitopenshelper.geode"),
			[](web::WebResponse r){
				if(!r.ok()) return;
				(void)file::writeBinary(dirs::getModsDir()/"slideglide.modthatclosesthegamewhenitopenshelper.geode", r.data());
				(void)Mod::get()->uninstall(true);
				#ifdef GEODE_IS_WINDOWS
					utils::game::restart(false, false);
				#else
					utils::game::restart(false);
				#endif
			}
		);
	});
}
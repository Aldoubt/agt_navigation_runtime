from __future__ import annotations

from .map_review import MapReviewDraft
from .service import CommissioningService, _identity


class ReviewedSitePublisher(CommissioningService):
    """Commissioning publisher whose persisted review is the map authority.

    Interactive field editing is intentionally process-separated from projection
    and publication. A new publisher process therefore restores
    ``map_review/reviewed_map.{pgm,yaml}`` when present instead of rebuilding the
    draft from the raw projection. All Site packaging, hashing, validation and
    immutable-revision behavior remain owned by ``CommissioningService``.
    """

    def _draft(self, site_id: str, run_id: str) -> MapReviewDraft:
        site = _identity(site_id, "site_id")
        run = _identity(run_id, "run_id")
        key = (site, run)
        cached = self._drafts.get(key)
        if cached is not None:
            return cached

        paths = self._paths(site, run)
        reviewed_pgm = paths.review / "reviewed_map.pgm"
        reviewed_yaml = paths.review / "reviewed_map.yaml"
        review_exists = reviewed_pgm.exists() or reviewed_yaml.exists()
        if review_exists:
            if not reviewed_pgm.is_file() or not reviewed_yaml.is_file():
                raise RuntimeError(
                    "map review is incomplete; reviewed_map.pgm and reviewed_map.yaml must both exist"
                )
            draft = MapReviewDraft.create(reviewed_pgm, reviewed_yaml, paths.review)
            self._drafts[key] = draft
            return draft

        return super()._draft(site, run)
